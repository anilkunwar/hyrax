/*************************************************************************
*
*  Welcome to HYRAX!
*  Andrea M. Jokisaari
*  CASL/MOOSE
*
*  30 May 2012
*
*************************************************************************/


#include "Moose.h"
#include "HyraxApp.h"
#include "Factory.h"
#include "AppFactory.h"
#include "ActionFactory.h"
#include "MooseSyntax.h"

//Module Includes
#include "SolidMechanicsApp.h"
#include "TensorMechanicsApp.h"
#include "PhaseFieldApp.h"
#include "HeatConductionApp.h"
#include "MiscApp.h"

//Kernels
#include "ACTransformElasticDF.h"
#include "ACCoupledCalphad.h"
#include "CHCoupledCalphadSplit.h"
#include "CHPrecipMatrixElasticity.h"

//Auxiliary Kernels
#include "AuxDeltaGStar.h"
#include "AuxBulkEnergyCalphad.h"
#include "AuxGradientEnergy.h"
#include "AuxElasticEnergy.h"
#include "AuxCalphadElasticity.h"
#include "AuxElasticInteractionEnergy.h"
#include "AuxAMRNucleationProbability.h"
#include "AuxVolumetricNucleationRate.h"
#include "AuxDFchemDC.h"
#include "AuxDFelDC.h"
#include "AuxGrandPotential.h"

//Dirac Kernels

//Boundary Conditions
#include "StressBC.h"
#include "SimpleSplitCHFluxBC.h"

//Materials
#include "CalphadEnergyMaterial.h"
#include "CalphadAB1CD1Material.h"
#include "CalphadAB1CD2Material.h"
#include "ZrHCalphadDiffusivity.h"
#include "TwoPhaseLinearElasticMaterial.h"

//Initial Conditions
#include "PolySpecifiedSmoothCircleIC.h"
#include "EllipsoidIC.h"
#include "SmoothBoxIC.h"
#include "DiamondIC.h"
#include "DepletionRegionIC.h"

//Dampers

//Executioners
#include "MeshSolutionModify.h"

//Post Processors
#include "NucleiInformation.h"

//TimeSteppers

//Actions

//UserObjects
#include "NucleationLocationUserObject.h"
#include "NucleusIntroductionSolutionModifier.h"
#include "OneNucleusUserObject.h"

//Markers
#include "NucleationMarker.h"


template<>
InputParameters validParams<HyraxApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("use_legacy_output_syntax") = false;
  return params;
}

HyraxApp::HyraxApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  HyraxApp::registerObjects(_factory);

  // Register Modules
  PhaseFieldApp::registerObjects(_factory);
  SolidMechanicsApp::registerObjects(_factory);
  TensorMechanicsApp::registerObjects(_factory);
  HeatConductionApp::registerObjects(_factory);
  MiscApp::registerObjects(_factory);

  // Associate Syntax from SolidMechanics Module
  Moose::associateSyntax(_syntax, _action_factory);
  PhaseFieldApp::associateSyntax(_syntax, _action_factory);
  SolidMechanicsApp::associateSyntax(_syntax, _action_factory);
  TensorMechanicsApp::associateSyntax(_syntax, _action_factory);
  HeatConductionApp::associateSyntax(_syntax, _action_factory);
  MiscApp::associateSyntax(_syntax, _action_factory);

  //Associate syntax for Hyrax Actions
  HyraxApp::associateSyntax(_syntax, _action_factory);
}

extern "C" void HyraxApp__registerApps() { HyraxApp::registerApps(); }
void
HyraxApp::registerApps()
{
  registerApp(HyraxApp);
}

void
HyraxApp::registerObjects(Factory & factory)
{
  //Kernels
  registerKernel(ACTransformElasticDF);
  registerKernel(ACCoupledCalphad);
  registerKernel(CHCoupledCalphadSplit);
  registerKernel(CHPrecipMatrixElasticity);

  //Auxiliary Kernels
  registerAux(AuxDeltaGStar);
  registerAux(AuxBulkEnergyCalphad);
  registerAux(AuxGradientEnergy);
  registerAux(AuxElasticEnergy);
  registerAux(AuxCalphadElasticity);
  registerAux(AuxElasticInteractionEnergy);
  registerAux(AuxAMRNucleationProbability);
  registerAux(AuxVolumetricNucleationRate);
  registerAux(AuxDFchemDC);
  registerAux(AuxDFelDC);
  registerAux(AuxGrandPotential);

  //Dirac Kernels

  //Boundary Conditions
  registerBoundaryCondition(StressBC);
  registerBoundaryCondition(SimpleSplitCHFluxBC);

  //Materials
  registerMaterial(CalphadEnergyMaterial);
  registerMaterial(CalphadAB1CD1Material);
  registerMaterial(CalphadAB1CD2Material);
  registerMaterial(ZrHCalphadDiffusivity);
  registerMaterial(TwoPhaseLinearElasticMaterial);

  //Initial Conditions
  registerInitialCondition(PolySpecifiedSmoothCircleIC);
  registerInitialCondition(EllipsoidIC);
  registerInitialCondition(SmoothBoxIC);
  registerInitialCondition(DiamondIC);
  registerInitialCondition(DepletionRegionIC);

  //Dampers

  //Executioners
  registerExecutioner(MeshSolutionModify);

  //Postprocessors
  registerPostprocessor(NucleiInformation);

  //TimeSteppers

  // UserObjects
  registerUserObject(NucleationLocationUserObject);
  registerUserObject(NucleusIntroductionSolutionModifier);
  registerUserObject(OneNucleusUserObject);

  // Markers
  registerMarker(NucleationMarker);

}

void
HyraxApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  // Actions
}
