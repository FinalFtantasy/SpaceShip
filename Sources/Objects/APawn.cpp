#include "APawn.h"


void APawn::TakeDamage(FDamage& STDamage)
{
    if (STDamage.Damage > HP)
    {
        HP = 0;
    }
    else
    {
        HP -= STDamage.Damage;
    }

    OnHpChanged();
}

void APawn::OnHpChanged()
{
}
