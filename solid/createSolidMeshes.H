    PtrList<fvMesh> solidRegions(rp.solidRegionNames().size());

    forAll(rp.solidRegionNames(), i)
    {
        Info<< "Create solid mesh for region " << rp.solidRegionNames()[i]
            << " for time = " << runTime.timeName() << nl << endl;

        solidRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    rp.solidRegionNames()[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );
    }

