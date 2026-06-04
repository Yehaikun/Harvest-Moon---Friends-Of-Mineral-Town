// 🔧 辅助函数 0x0809BFE8 - 角色/精灵相关

#include "prelude.h"

#include "actor.hh"

struct Unk_Actor_0809BFE8 : Actor
{
    Unk_Actor_0809BFE8();

    u32 unk_08_0 : 7;
    u32 unk_0C;
};

Unk_Actor_0809BFE8::Unk_Actor_0809BFE8()
    : Actor(ActorLocation(Location(MAP_NONE, 0, 0), 0)), unk_08_0(100), unk_0C(0)
{
}

EC Unk_Actor_0809BFE8 * func_0809BFE8() ALIAS(__18Unk_Actor_0809BFE8);

EC unsigned int func_0809C060(Unk_Actor_0809BFE8 const & self)
{
    return self.unk_08_0;
}

EC void func_0809C068(Unk_Actor_0809BFE8 & self, int arg_0)
{
    int val = self.unk_08_0 - arg_0;

    if (val < 0)
        val = 0;
    else if (val > 100)
        val = 100;

    self.unk_08_0 = val;
}

EC void func_0809C098(Unk_Actor_0809BFE8 & self)
{
    self.unk_0C = 0;
}

/* what follows shouldn't be hard except that to do it well I think there needs to be union/placeholder shenanigans */
