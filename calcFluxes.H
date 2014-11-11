forAll(fluidRegions,i)
{
    Info<< "Calculating fluxes for fluid region " 
	<< fluidRegions[i].name() << nl << endl; 

    fvMesh& mesh =  fluidRegions[i];
    volScalarField& c1 = c1f[i];
    volScalarField& c2 = c2f[i];
    volScalarField& phiV = phiVf[i];
    volVectorField& U = Uf[i];

    surfaceScalarField c1Flux
    (
	"c1Flux",
	-D1*fvc::snGrad(c1)
	-z1*D1/kBT*eCharge*fvc::snGrad(phiV)*fvc::interpolate(c1)
	+(fvc::interpolate(U) & mesh.Sf())/mesh.magSf()*fvc::interpolate(c1)
    );

    surfaceScalarField c2Flux
    (
	"c2Flux",
	-D2*fvc::snGrad(c2)
	-z2*D2/kBT*eCharge*fvc::snGrad(phiV)*fvc::interpolate(c2)
	+(fvc::interpolate(U) & mesh.Sf())/mesh.magSf()*fvc::interpolate(c2)
    );

    surfaceScalarField cFlux = NA*eCharge*(z1*c1Flux+z2*c2Flux);

    surfaceScalarField::GeometricBoundaryField& IFlux = cFlux.boundaryField();

    Info<< "  Calculating total current\n" << endl;
    forAll(IFlux, patchi)
    {
        Info<< mesh.boundary()[patchi].name()
            << " "
            << gSum
               (
                   mesh.magSf().boundaryField()[patchi]
                   *IFlux[patchi]
               )
            << endl;
    }
    Info<< endl;

    if(solveFlow)
    {
	surfaceScalarField phi
	(
	    "phi",
	    fvc::interpolate(U) & mesh.Sf()
	);

	surfaceScalarField::GeometricBoundaryField& qFlux = phi.boundaryField();

        Info<< "  Calculating total flow rate\n" << endl;
        forAll(qFlux, patchi)
        {
	   Info<< mesh.boundary()[patchi].name()
	       << " "
	       << gSum
	          (
	              qFlux[patchi]
	   	  )
	       << endl;
    	}
    	Info<< endl;
    }
}
