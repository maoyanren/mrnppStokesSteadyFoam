/*------------------ creating solid fields --------------------*/

PtrList<volScalarField> phiVs(solidRegions.size());
PtrList<volScalarField> eps(solidRegions.size());
PtrList<volVectorField> Es(solidRegions.size());

forAll(solidRegions,i)
{
    Info<< "  creating solid fields for region "
        << solidRegions[i].name() << nl << endl;

    Info<< "  creating phiV\n" << endl;
    phiVs.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "phiV",
                runTime.timeName(),
                solidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            solidRegions[i]
        )
    );

    Info<< "  Reading epsilonr\n" << endl;
    eps.set
    (
	i,
	new volScalarField
	(
	    IOobject
            (
                "epr",
                runTime.timeName(),
                solidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
	    solidRegions[i]
	)
    );

    Es.set
    (
        i,
        new volVectorField
        (
            IOobject
            (
                "E",
                runTime.timeName(),
                solidRegions[i],
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -fvc::grad(phiVs[i])
        )
    );
}

/*---------------------------------------------------------------*/

    
