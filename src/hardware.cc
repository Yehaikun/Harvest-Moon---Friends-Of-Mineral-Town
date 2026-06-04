// 🖥️ 硬件抽象 - GBA 硬件寄存器操作封装

#include "prelude.h"

union Unk_hardware_ent_080D6D98
{
    Unk_hardware_ent_080D6D98 * next_free;

    struct
    {
        u16 unk_00;
        u16 unk_02;
    } params;
};

EC Unk_hardware_ent_080D6D98 * func_080D6D98(Unk_hardware_ent_080D6D98 * self, int num, int val);

struct Unk_hardware_03000404
{
    Unk_hardware_03000404()
    {
        unk_00 = func_080D6D98(unk_04, 0x10, 0);
        unk_44 = 0;
        unk_48 = 0;
        unk_4C = 0;
        unk_50 = 0;
        unk_51 = 0;
        unk_44 = 0;
    }

    bool inl_pred_0(unsigned int idx) const { return idx < 0x10 && (unk_44 & (1 << (idx % 0x20u))) != 0; }

    void inl_func_0(unsigned int idx)
    {
        if (idx < 0x10)
            unk_44 &= ~(1 << (idx % 0x20u));
    }

    void inl_func_1(unsigned int idx)
    {
        if (idx < 0x10)
            unk_44 |= (1 << (idx % 0x20u));
    }

    Unk_hardware_ent_080D6D98 & GetEntry(unsigned int idx) { return unk_04[idx]; }

    unsigned int IndexOf(Unk_hardware_ent_080D6D98 const * ent) const { return ent - unk_04; }

    void FreeEntry(Unk_hardware_ent_080D6D98 * ent)
    {
        ent->next_free = unk_00;
        unk_00 = ent;
    }

    Unk_hardware_ent_080D6D98 * AllocEntry(Unk_hardware_ent_080D6D98 * ent)
    {
        Unk_hardware_ent_080D6D98 * prev = unk_00;

        if (ent != nullptr)
            unk_00 = ent->next_free;

        return prev;
    }

    /* +00 */ Unk_hardware_ent_080D6D98 * unk_00;
    /* +04 */ Unk_hardware_ent_080D6D98 unk_04[0x10];
    /* +44 */ u32 unk_44;
    /* +48 */ u16 unk_48;
    /* +4A */ u16 unk_4A;
    /* +4C */ u32 unk_4C;
    /* +50 */ u8 unk_50;
    /* +51 */ u8 unk_51;
};

extern Unk_hardware_03000404 * gUnk_03000404;

struct Unk_hardware_H
{
    ~Unk_hardware_H();
};

EC Unk_hardware_H * func_08007128(Unk_hardware_H * self)
{
    if (gUnk_03000404 == nullptr)
    {
        gUnk_03000404 = new Unk_hardware_03000404;
    }

    gUnk_03000404->unk_4C++;

    return self;
}

EC Unk_hardware_H * func_08007174(Unk_hardware_H * self, Unk_hardware_H const & other)
{
    gUnk_03000404->unk_4C++;

    return self;
}

Unk_hardware_H::~Unk_hardware_H()
{
    gUnk_03000404->unk_4C--;

    if (gUnk_03000404->unk_4C == 0)
    {
        if (gUnk_03000404 != nullptr)
            delete gUnk_03000404;

        gUnk_03000404 = nullptr;
    }
}

EC void func_08007184(Unk_hardware_H * self) ALIAS(_._14Unk_hardware_H);

EC void func_080071BC(Unk_hardware_H * self, unsigned int from, unsigned int count)
{
    // https://decomp.me/scratch/e4deE (solved, but messy)

    (void)self;

    Unk_hardware_03000404 * h = gUnk_03000404;

    if (h->unk_51 != 0)
    {
        for (unsigned int i = h->unk_50, end = h->unk_50 + h->unk_51; i < end; i++)
        {
            if (h->inl_pred_0(i))
            {
                h->FreeEntry(&h->GetEntry(i));
                h->inl_func_0(i);
            }
        }

        h->unk_51 = 0;
    }

    if (count != 0)
    {
        unsigned int to = count + from;

        for (unsigned int i = 0; i < 0x10; i++)
        {
            if (h->inl_pred_0(i))
            {
                if (from <= i && i < to)
                {
                    h->GetEntry(i).params.unk_02 = 0;
                    h->FreeEntry(&h->GetEntry(i));
                    h->inl_func_0(i);
                    h->unk_48--;
                }
            }
        }

        unsigned int alloc_mask = 0;
        unsigned int target_mask = ((1 << count) - 1u) << from;

        for (;;)
        {
            Unk_hardware_ent_080D6D98 * ent = h->AllocEntry(h->unk_00);

            if (ent == nullptr)
                goto alloc_loop; /* break doesn't match D= */

            h->inl_func_1(h->IndexOf(ent));
            alloc_mask |= 1u << h->IndexOf(ent);

            if ((alloc_mask & target_mask) == target_mask)
                break;
        }

    alloc_loop:
        for (unsigned int i = 0; (alloc_mask & ~target_mask) != 0 && i < 0x10; i++)
        {
            unsigned int bit = 1u << i;

            if (alloc_mask & bit & ~target_mask)
            {
                h->FreeEntry(&h->GetEntry(i));
                h->inl_func_0(i);

                alloc_mask &= ~bit;
            }
        }

        h->unk_50 = from;
        h->unk_51 = count;
    }
}
