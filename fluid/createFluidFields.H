/*-------------------- create fluid fields ---------------------*/

PtrList<volScalarField> c1f(fluidRegions.size());
PtrList<volScalarField> c2f(fluidRegions.size());
PtrList<volScalarField> phiVf(fluidRegions.size());
PtrList<volVectorField> Uf(fluidRegions.size());
PtrList<surfaceScalarField> phif(fluidRegions.size());
PtrList<volScalarField> pf(fluidRegions.size());
PtrList<volScalarField> epf(fluidRegions.size());
PtrList<volVectorField> Ef(fluidRegions.size());

List<label> pRefCellf(fluidRegions.size(), 0);
List<scalar> pRefValuef(fluidRegions.size(), 0.0);

forAll(fluidRegions,i)
{
    Info<< "  creating fluid fields for region "
        << fluidRegions[i].name() << nl << endl;

    Info<< "  creating c1\n" << endl;
    c1f.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "c1",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    Info<< "  creating c2\n" << endl;
    c2f.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "c2",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    Info<< "  creating phiV\n" << endl;
    phiVf.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "phiV",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    Info<< "  Creating U\n" << endl;
    Uf.set
    (
        i,
        new volVectorField
        (
            IOobject
            (
                "U",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    phif.set
    (
        i,
        new surfaceScalarField
        (
            IOobject
            (
                "phi",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::READ_IF_PRESENT,
                IOobject::AUTO_WRITE
            ),
            linearInterpolate(Uf[i])
                & fluidRegions[i].Sf()
        )
    );

    Info<< "  Creating p\n" << endl;
    pf.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "p",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    Info<< "  reading epsilonr\n" << endl;
    epf.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "epr",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
	    fluidRegions[i]
        )
    );

    Ef.set
    (
        i,
        new volVectorField
        (
            IOobject
            (
                "E",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -fvc::grad(phiVf[i])
        )
    );

    // setting reference pressure and cell
    setRefCell
    (
        pf[i],
        fluidRegions[i].solutionDict().subDict("mrNPPStokesSteadyControl"),
        pRefCellf[i],
        pRefValuef[i]
    );

}
