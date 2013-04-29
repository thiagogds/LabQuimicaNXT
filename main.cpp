#include <app.h>
#include "assets.gen.h"

using namespace Sifteo;

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(GameAssets);

static AssetSlot BecherSlot = AssetSlot::allocate().bootstrap(BecherAssets);

static AssetSlot PhSlot = AssetSlot::allocate().bootstrap(PhAssets);

static Metadata M = Metadata()
    .title("Sifteo Chemistry Lab")
    .package("moleque.lab.quimica", "0.1")
    .icon(Icon)
    .cubeRange(4);

void main()
{
    App app;
    app.init();

    app.run();
}


