/* --------------- Reading constants -------------- */
    
    Info<< "Reading constants\n" << endl;
    IOdictionary constants
    (
        IOobject
        (
            "constants",
            runTime.time().constant(),
            runTime.db(),
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    dimensionedScalar epsilon0
    (
        constants.lookup("epsilon0")
    );

    dimensionedScalar z1
    (
        constants.lookup("z1")
    );	

    dimensionedScalar z2
    (
        constants.lookup("z2")
    );

    dimensionedScalar D1
    (
        constants.lookup("D1")
    );

    dimensionedScalar D2
    (
        constants.lookup("D2")
    );
    
    dimensionedScalar kBT
    (
        constants.lookup("kBT")
    );

    dimensionedScalar NA
    (
        constants.lookup("NA")
    );

    dimensionedScalar eCharge
    (
	constants.lookup("eCharge")
    );

    dimensionedScalar nu
    (
        constants.lookup("nu")
    );

    dimensionedScalar rho
    (
        constants.lookup("rho")
    );
