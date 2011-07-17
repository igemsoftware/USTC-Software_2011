#ifndef ITEMREGISTRY_H
#define ITEMREGISTRY_H

#include <QMap>

template<class SRC, class DEST>
class ItemRegistry
{
public:
    static const DEST& accessor(bool isRead, const SRC& src, const DEST* dest = 0)
    {
        static QMap<SRC, DEST> registry;
        if(isRead)
        {
            return registry[src];
        }
        else
        {
            return (registry[src] = *dest);
        }
    }

    static inline const DEST& find(const SRC& src)
    {
        return accessor(true, src);
    }

    static inline void set(const SRC& src, const DEST* dest = 0)
    {
        accessor(false, src, dest);
    }

public:
    struct ItemRegistryInlineAdd
    {
        ItemRegistryInlineAdd(const SRC& src, const DEST& dest)
        {
            ItemRegistry<SRC, DEST>::set(src, &dest);
        }
    };
};

#endif // ITEMREGISTRY_H
