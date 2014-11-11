    // solve Poisson equation
    phiV.storePrevIter();
    phiV.boundaryField().updateCoeffs();
    fvScalarMatrix phiVEqn		
    (
        -fvm::laplacian(epsilonr, phiV)
    );
    phiVEqn.relax();
    solve
    (
	phiVEqn == NA*eCharge*(z1*c1+z2*c2)/epsilon0
    );
    
    E = -fvc::grad(phiV);

    // solve Nernst-Planck equation
    c1.storePrevIter();
    c2.storePrevIter();

    Info<< "\nSolving for c in fluid region "
	<< fluidRegions[i].name() << endl;

    //~ c1	
    surfaceScalarField rhoFlux1
    (
        -z1*D1/kBT*eCharge*fvc::snGrad(phiV)*mesh.magSf()
    );
    c1.boundaryField().updateCoeffs();
    fvScalarMatrix c1Eqn
    (
        fvm::div(rhoFlux1, c1) + fvm::div(phi,c1) - fvm::laplacian(D1, c1)
    );
    c1Eqn.relax();
    c1Eqn.solve();
    
    //~ c2
    surfaceScalarField rhoFlux2
    (
        -z2*D2/kBT*eCharge*fvc::snGrad(phiV)*mesh.magSf()
    );
    c2.boundaryField().updateCoeffs();        
    fvScalarMatrix c2Eqn
    (
        fvm::div(rhoFlux2, c2) + fvm::div(phi,c2) - fvm::laplacian(D2, c2)
    );
    c2Eqn.relax();
    c2Eqn.solve();
