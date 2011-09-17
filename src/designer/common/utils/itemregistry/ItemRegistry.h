#ifndef ITEMREGISTRY_H
#define ITEMREGISTRY_H

#include <QMap>

template<class SRC, class DEST>
class ItemRegistry
{
protected:
    static QMap<SRC, DEST>& getRegistry()
    {
        static QMap<SRC, DEST> registry;
        return registry;
    }
public:
    static inline int count()
    {
        return getRegistry().count();
    }

    static inline const DEST item(int index)
    {
        return getRegistry().values()[index];
    }

    static inline const DEST& find(const SRC& src)
    {
        return getRegistry()[src];
    }

    static inline void set(const SRC& src, const DEST& dest)
    {
        getRegistry()[src]=dest;
    }

public:
    struct ItemRegistryInlineAdd
    {
        ItemRegistryInlineAdd(const SRC& src, const DEST& dest)
        {
            ItemRegistry<SRC, DEST>::set(src, dest);
        }
    };
};

#endif // ITEMREGISTRY_H
