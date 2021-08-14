# vshPatch
Like repatch, but for system applications

Ever wanted to make a modification to vs0, but dont like the hastle of having to reinstall the OS if something breaks?
maybe want to try modify some RCO's or enable package installer? well now this is an "emulated VS0",
simply put your changes you want to make into ux0:/vshPatch/ and then the changes will be reflected in "vs0:" partition,
via the power of fios2

btw, the fios overlay type is 1, so writes will still goto real VS0 *assuming its read/write mounted
