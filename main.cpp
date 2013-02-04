#include <app.h>
#include "assets.gen.h"

using namespace Sifteo;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

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


