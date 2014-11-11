    fvMesh& mesh = solidRegions[i];
    volScalarField& phiV = phiVs[i];
    volVectorField& E = Es[i];
    const volScalarField& epsilonr = eps[i];
