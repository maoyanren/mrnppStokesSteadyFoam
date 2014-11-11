
    U.storePrevIter();
    tmp<fvVectorMatrix> UEqn
    (
        -fvm::laplacian(nu, U)
    );
    UEqn().relax();

    solve
    (
        UEqn() == 
	- fvc::grad(p)
	- NA*eCharge/rho*(z1*c1+z2*c2)*fvc::grad(phiV)
    );

    // pressure-velocity coupling
    p.storePrevIter();
    p.boundaryField().updateCoeffs();

    volScalarField rAU(1.0/UEqn().A());
    U = rAU*(UEqn().H() - NA*eCharge/rho*(z1*c1+z2*c2)*fvc::grad(phiV));
    UEqn.clear();
    
    phi = fvc::interpolate(U) & mesh.Sf();
    adjustPhi(phi, U, p);

    for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
        fvScalarMatrix pEqn
        (
            fvm::laplacian(rAU, p) == fvc::div(phi)
        );

        pEqn.setReference(pRefCell, pRefValue);
        pEqn.solve();

        if(nonOrth == nNonOrthCorr)
	{
	    phi -= pEqn.flux();
	}
    }

    #include "continuityErrs.H"

    p.relax();

    U -= rAU*fvc::grad(p);
    U.correctBoundaryConditions();
    
