    phiV.storePrevIter();
    phiV.boundaryField().updateCoeffs();

    fvScalarMatrix phiVEqn
    (
	fvm::laplacian(phiV)
    );
    phiVEqn.relax();

    phiVEqn.solve();

    E = -fvc::grad(phiV);


