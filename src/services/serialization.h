#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "../core/constants.h"
#include "qlist.h"
#include "qstring"

template<class TModel>
class ISerializable
{
public:
    data_size_t size() const { return get_impl()->size_impl(); }
    auto as_tuple() { return get_impl()->as_tuple_impl(); }
    auto as_tuple() const { return get_impl()->as_tuple_impl(); }

private:
    TModel* get_impl() { return static_cast<TModel*>(this); }
    const TModel* get_impl() const { return static_cast<const TModel*>(this); }
};

template<class TModel>
concept Serializable = std::is_base_of_v<ISerializable<TModel>, TModel>;

template<class TModel>
concept SerializableList = std::is_same_v<TModel, QList<typename TModel::value_type>>
                           && Serializable<typename TModel::value_type>;

class Serializer
{
public:
    template<class TModel>
    static data_t serialize(const TModel& model)
    {
        data_size_t offset = 0;
        data_t data;

        if constexpr (Serializable<TModel>)
        {
            data.resize(model.size());
            serialize_tuple(data, model.as_tuple(), &offset);
        }
        else if constexpr (SerializableList<TModel>)
        {
            serialize_list(data, model, &offset);
        }

        return data;
    }

    template<class TModel>
    static TModel deserialize(const data_t& data)
    {
        data_size_t offset = 0;
        TModel model{};

        if constexpr (Serializable<TModel>)
        {
            auto tuple = model.as_tuple();
            deserialize_tuple(data, tuple, &offset);
        }
        else if constexpr (SerializableList<TModel>)
        {
            deserialize_list(data, model, &offset);
        }

        return model;
    }

private:
    template<class... Args>
    static void serialize_tuple(data_t& data, const std::tuple<const Args&...>& tuple, data_size_t* offset)
    {
        std::apply([&](const auto&... args) { (internal_serialize(data, args, offset), ...); }, tuple);
    }

    template<class... Args>
    static void deserialize_tuple(const data_t& data, std::tuple<Args&...>& tuple, data_size_t* offset)
    {
        std::apply([&](auto&... args) { (internal_deserialize(data, args, offset), ...); }, tuple);
    }

    template<class TModel>
    static void serialize_list(data_t& data, const QList<TModel>& model, data_size_t* offset)
    {
        data_size_t data_size = DATA_SIZE;
        for (const TModel& item : model)
        {
            data_size += DATA_SIZE;
            data_size += item.size();
        }

        data.resize(data_size);

        // vector size
        data_size_t vector_size = static_cast<data_size_t>(model.size());
        std::memcpy(data.data() + *offset, &vector_size, DATA_SIZE);
        *offset += DATA_SIZE;

        for (const TModel& item : model)
        {
            // item size
            data_size_t item_size = static_cast<data_size_t>(item.size());
            std::memcpy(data.data() + *offset, &item_size, DATA_SIZE);
            *offset += DATA_SIZE;

            serialize_tuple(data, item.as_tuple(), offset);
        }
    }

    template<class TModel>
    static void deserialize_list(const data_t& data, QList<TModel>& model, data_size_t* offset)
    {
        // vector size
        data_size_t vector_size = 0;
        std::memcpy(&vector_size, data.data() + *offset, DATA_SIZE);
        *offset += DATA_SIZE;

        model.reserve(vector_size);

        while (vector_size-- > 0)
        {
            // item size
            data_size_t item_size = 0;
            std::memcpy(&item_size, data.data() + *offset, DATA_SIZE);
            *offset += DATA_SIZE;

            model.emplace_back();
            auto tuple = model.back().as_tuple();
            deserialize_tuple(data, tuple, offset);
        }
    }

    template<class TModel>
    static void internal_serialize(data_t& data, const TModel& model, data_size_t* offset)
    {
        if constexpr (std::is_trivially_copyable_v<TModel>)
        {
            serialize_trivially_copyable_type(data, model, offset);
        }
        else if constexpr (std::is_same_v<TModel, QString>)
        {
            serialize_string(data, model, offset);
        }
    }

    template<class TModel>
    static void internal_deserialize(const data_t& data, TModel& model, data_size_t* offset)
    {
        if constexpr (std::is_trivially_copyable_v<TModel>)
        {
            deserialize_trivially_copyable_type(data, model, offset);
        }
        else if constexpr (std::is_same_v<TModel, QString>)
        {
            deserialize_string(data, model, offset);
        }
    }

    template<class TModel>
    static void serialize_trivially_copyable_type(data_t& data, const TModel& model, data_size_t* offset)
    {
        std::memcpy(data.data() + *offset, &model, sizeof(TModel));
        *offset += sizeof(TModel);
    }

    template<class TModel>
    static void deserialize_trivially_copyable_type(const data_t& data, TModel& model, data_size_t* offset)
    {
        std::memcpy(&model, data.data() + *offset, sizeof(TModel));
        *offset += sizeof(TModel);
    }

    static void serialize_string(data_t& data, const QString& model, data_size_t* offset)
    {
        // string size
        const data_size_t string_size = static_cast<const data_size_t>(model.size());
        std::memcpy(data.data() + *offset, &string_size, DATA_SIZE);
        *offset += DATA_SIZE;

        // string
        std::memcpy(data.data() + *offset, model.data(), string_size);
        *offset += string_size;
    }

    static void deserialize_string(const data_t& data, QString& model, data_size_t* offset)
    {
        // string size
        data_size_t string_size = 0;
        std::memcpy(&string_size, data.data() + *offset, DATA_SIZE);
        *offset += DATA_SIZE;

        // string
        model = QString::fromUtf8(data.data() + *offset, string_size);
        *offset += string_size;
    }
};

#endif // SERIALIZATION_H
