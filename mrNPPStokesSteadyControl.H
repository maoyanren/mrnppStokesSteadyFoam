    // We do not have a top-level mesh. Construct the fvSolution for
    // the runTime instead.

    fvSolution solutionDict(runTime);

    const dictionary& control = solutionDict.subDict("mrNPPStokesSteadyControl");

    const int nNonOrthCorr = control.lookupOrDefault<int>("nNonOrthogonalCorrectors", 1);

    const bool fixU = control.lookupOrDefault<bool>("fixU", false);

    const bool fixNPP = control.lookupOrDefault<bool>("fixNPP", true);

    // convergence criteria

    const dictionary& residualDict = solutionDict.subDict("residualControl");

    scalar delta_c1_max = residualDict.lookupOrDefault<scalar>("delta_c1_max", 1e-06);

    scalar delta_c2_max = residualDict.lookupOrDefault<scalar>("delta_c2_max", 1e-06);

    scalar delta_phiV_max = residualDict.lookupOrDefault<scalar>("delta_phiV_max", 1e-06);

    scalar delta_U_max = residualDict.lookupOrDefault<scalar>("delta_U_max", 1e-06);

    scalar delta_p_max = residualDict.lookupOrDefault<scalar>("delta_p_max", 1e-06);
