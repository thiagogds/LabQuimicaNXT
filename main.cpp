#include <app.h>
#include "assets.gen.h"

using namespace Sifteo;

static AssetSlot MainSlot = AssetSlot::allocate().bootstrap(GameAssets);

static AssetSlot PipeteSlot = AssetSlot::allocate().bootstrap(PipeteAssets);

static AssetSlot BecherSlot = AssetSlot::allocate().bootstrap(BecherAssets);

static Metadata M = Metadata()
    .title("Sifteo Chemistry Lab")
    .package("moleque.lab.quimica", "0.1")
    .icon(Icon)
    .cubeRange(3);

void main()
{
    App app;
    app.init();

    while (1) {
	    app.run();
	}
}


