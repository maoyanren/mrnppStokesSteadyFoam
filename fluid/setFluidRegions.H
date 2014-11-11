    fvMesh& mesh =  fluidRegions[i];
    volScalarField& c1 = c1f[i];
    volScalarField& c2 = c2f[i];
    volScalarField& phiV = phiVf[i];
    const volScalarField& epsilonr = epf[i];
    volVectorField& E = Ef[i];

    volVectorField& U = Uf[i];
    surfaceScalarField& phi = phif[i];
    volScalarField& p = pf[i];

    const label pRefCell =  pRefCellf[i];
    const scalar pRefValue = pRefValuef[i];

    
