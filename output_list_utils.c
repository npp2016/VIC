#include <stdio.h>
#include <stdlib.h>
#include <vicNl.h>
#include <string.h>

static char vcid[] = "$Id$";

out_data_struct *create_output_list() {
/*************************************************************
  create_output_list()      Ted Bohn     September 08, 2006

  This routine creates the list of output variables.

  Modifications:
  2006-Sep-14 Implemented ALMA-compliant input and output;
              now more variables are tracked.  TJB
  2006-Sep-18 Implemented aggregation of output variables.  TJB

*************************************************************/

  extern option_struct options;
  int v;
  out_data_struct *out_data;

  out_data = (out_data_struct *)calloc(N_OUTVAR_TYPES,sizeof(out_data_struct));

  // Build the list of supported output variables

  // Water Balance Terms - state variables
  strcpy(out_data[OUT_LAKE_DEPTH].varname,"OUT_LAKE_DEPTH");           /* lake depth [m] */
  out_data[OUT_LAKE_DEPTH].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_ICE].varname,"OUT_LAKE_ICE");               /* moisture stored as lake ice [mm] */
  out_data[OUT_LAKE_ICE].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_ICE_FRACT].varname,"OUT_LAKE_ICE_FRACT");   /* fractional coverage of lake ice [fraction] */
  out_data[OUT_LAKE_ICE_FRACT].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_ICE_HEIGHT].varname,"OUT_LAKE_ICE_HEIGHT"); /* thickness of lake ice [cm] */
  out_data[OUT_LAKE_ICE_HEIGHT].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_MOIST].varname,"OUT_LAKE_MOIST");           /* liquid water stored in lake [mm over lake area?] */
  out_data[OUT_LAKE_MOIST].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_SURF_AREA].varname,"OUT_LAKE_SURF_AREA");   /* lake surface area [m2] */
  out_data[OUT_LAKE_SURF_AREA].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_VOLUME].varname,"OUT_LAKE_VOLUME");         /* lake volume [m3] */
  out_data[OUT_LAKE_VOLUME].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_ROOTMOIST].varname,"OUT_ROOTMOIST");             /* root zone soil moisture [mm] */
  out_data[OUT_ROOTMOIST].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SMFROZFRAC].varname,"OUT_SMFROZFRAC");           /* fraction of soil moisture (by mass) that is ice, for each soil layer */
  out_data[OUT_SMFROZFRAC].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SMLIQFRAC].varname,"OUT_SMLIQFRAC");             /* fraction of soil moisture (by mass) that is liquid, for each soil layer */
  out_data[OUT_SMLIQFRAC].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SNOW_CANOPY].varname,"OUT_SNOW_CANOPY");         /* snow interception storage in canopy [mm] */
  out_data[OUT_SNOW_CANOPY].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SNOW_COVER].varname,"OUT_SNOW_COVER");           /* fractional area of snow cover [fraction] */
  out_data[OUT_SNOW_COVER].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SNOW_DEPTH].varname,"OUT_SNOW_DEPTH");           /* depth of snow pack [cm] */
  out_data[OUT_SNOW_DEPTH].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SOIL_ICE].varname,"OUT_SOIL_ICE");               /* soil ice content [mm] for each soil layer */
  out_data[OUT_SOIL_ICE].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SOIL_LIQ].varname,"OUT_SOIL_LIQ");               /* soil liquid moisture content [mm] for each soil layer */
  out_data[OUT_SOIL_LIQ].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SOIL_MOIST].varname,"OUT_SOIL_MOIST");           /* soil total moisture content [mm] for each soil layer */
  out_data[OUT_SOIL_MOIST].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SOIL_WET].varname,"OUT_SOIL_WET");               /* vertical average of (soil moisture - wilting point)/(maximum soil moisture - wilting point) [mm/mm] */
  out_data[OUT_SOIL_WET].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SURFSTOR].varname,"OUT_SURFSTOR");               /* storage of liquid water on surface (ponding) [mm] */
  out_data[OUT_SURFSTOR].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SURF_FROST_FRAC].varname,"OUT_SURF_FROST_FRAC"); /* fraction of soil surface that is frozen [fraction] */
  out_data[OUT_SURF_FROST_FRAC].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SWE].varname,"OUT_SWE");                         /* snow water equivalent in snow pack [mm] */
  out_data[OUT_SWE].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_WDEW].varname,"OUT_WDEW");                       /* total moisture interception storage in canopy [mm] */
  out_data[OUT_WDEW].aggtype = AGG_TYPE_END;

  // Water Balance Terms - fluxes
  strcpy(out_data[OUT_BASEFLOW].varname,"OUT_BASEFLOW");               /* baseflow out of the bottom layer [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_BASEFLOW].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_DELINTERCEPT].varname,"OUT_DELINTERCEPT");       /* change in canopy interception storage [mm] */
  out_data[OUT_DELINTERCEPT].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_DELSOILMOIST].varname,"OUT_DELSOILMOIST");       /* change in soil water content [mm] */
  out_data[OUT_DELSOILMOIST].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_DELSWE].varname,"OUT_DELSWE");                   /* change in snow water equivalent [mm] */
  out_data[OUT_DELSWE].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_EVAP].varname,"OUT_EVAP");                       /* total net evaporation [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_EVAP].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_EVAP_BARE].varname,"OUT_EVAP_BARE");             /* net evaporation from bare soil [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_EVAP_BARE].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_EVAP_CANOP].varname,"OUT_EVAP_CANOP");           /* net evaporation from canopy interception [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_EVAP_CANOP].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_EVAP_LAKE].varname,"OUT_EVAP_LAKE");             /* net evaporation from lake surface [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_EVAP_LAKE].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_INFLOW].varname,"OUT_INFLOW");                   /* moisture that reaches top of soil column [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_INFLOW].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_PREC].varname,"OUT_PREC");                       /* incoming precipitation [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_PREC].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_RAINF].varname,"OUT_RAINF");                     /* rainfall [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_RAINF].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_REFREEZE].varname,"OUT_REFREEZE");               /* refreezing of water in the snow [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_REFREEZE].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_RUNOFF].varname,"OUT_RUNOFF");                   /* surface runoff [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_RUNOFF].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SNOW_MELT].varname,"OUT_SNOW_MELT");             /* snow melt [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SNOW_MELT].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SNOWF].varname,"OUT_SNOWF");                     /* snowfall [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SNOWF].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SUB_BLOWING].varname,"OUT_SUB_BLOWING");         /* net sublimation of blowing snow [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SUB_BLOWING].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SUB_CANOP].varname,"OUT_SUB_CANOP");             /* net sublimation from snow stored in canopy [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SUB_CANOP].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SUB_SNOW].varname,"OUT_SUB_SNOW");               /* net sublimation from snow pack (surface and blowing) [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SUB_SNOW].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SUB_SURFACE].varname,"OUT_SUB_SURFACE");         /* net sublimation from snow pack surface [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SUB_SURFACE].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_TRANSP_VEG].varname,"OUT_TRANSP_VEG");           /* net transpiration from vegetation [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_TRANSP_VEG].aggtype = AGG_TYPE_SUM;

  // Energy Balance Terms - state variables
  strcpy(out_data[OUT_ALBEDO].varname,"OUT_ALBEDO");                   /* albedo [fraction] */
  out_data[OUT_ALBEDO].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_BARESOILT].varname,"OUT_BARESOILT");             /* bare soil surface temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_BARESOILT].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_FDEPTH].varname,"OUT_FDEPTH");                   /* depth of freezing fronts [cm] (ALMA_OUTPUT: [m]) for each freezing front */
  out_data[OUT_FDEPTH].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_LAKE_ICE_TEMP].varname,"OUT_LAKE_ICE_TEMP");     /* lake ice temperature [K] */
  out_data[OUT_LAKE_ICE_TEMP].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_LAKE_SURF_TEMP].varname,"OUT_LAKE_SURF_TEMP");   /* lake surface temperature [K] */
  out_data[OUT_LAKE_SURF_TEMP].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_RAD_TEMP].varname,"OUT_RAD_TEMP");               /* average radiative surface temperature [K] */
  out_data[OUT_RAD_TEMP].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SALBEDO].varname,"OUT_SALBEDO");                 /* snow albedo [fraction] */
  out_data[OUT_SALBEDO].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SNOW_PACK_TEMP].varname,"OUT_SNOW_PACK_TEMP");   /* snow pack temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_SNOW_PACK_TEMP].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SNOW_SURF_TEMP].varname,"OUT_SNOW_SURF_TEMP");   /* snow surface temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_SNOW_SURF_TEMP].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SOIL_TEMP].varname,"OUT_SOIL_TEMP");             /* soil temperature [C] (ALMA_OUTPUT: [K]) for each soil layer */
  out_data[OUT_SOIL_TEMP].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SURF_TEMP].varname,"OUT_SURF_TEMP");             /* average surface temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_SURF_TEMP].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_TDEPTH].varname,"OUT_TDEPTH");                   /* depth of thawing fronts [cm] (ALMA_OUTPUT: [m]) for each thawing front */
  out_data[OUT_TDEPTH].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_VEGT].varname,"OUT_VEGT");                       /* average vegetation canopy temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_VEGT].aggtype = AGG_TYPE_AVG;

  // Energy Balance Terms - fluxes
  strcpy(out_data[OUT_ADVECTED_SENSIBLE].varname,"OUT_ADVECTED_SENSIBLE"); /* net sensible heat advected to snow pack [W/m2] */
  out_data[OUT_ADVECTED_SENSIBLE].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_ADVECTION].varname,"OUT_ADVECTION");             /* advected energy [W/m2] */
  out_data[OUT_ADVECTION].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_DELTACC].varname,"OUT_DELTACC");                 /* rate of change in cold content in snow pack [W/m2] */
  out_data[OUT_DELTACC].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_DELTAH].varname,"OUT_DELTAH");                   /* rate of change in heat storage [W/m2] */
  out_data[OUT_DELTAH].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_ENERGY_ERROR].varname,"OUT_ENERGY_ERROR");       /* energy budget error [W/m2] */
  out_data[OUT_ENERGY_ERROR].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_FUSION].varname,"OUT_FUSION");                   /* net energy used to melt/freeze soil moisture [W/m2] */
  out_data[OUT_FUSION].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_GRND_FLUX].varname,"OUT_GRND_FLUX");             /* net heat flux into ground [W/m2] */
  out_data[OUT_GRND_FLUX].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_LATENT].varname,"OUT_LATENT");                   /* net upward latent heat flux [W/m2] */
  out_data[OUT_LATENT].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_LATENT_SUB].varname,"OUT_LATENT_SUB");           /* net upward latent heat flux from sublimation [W/m2] */
  out_data[OUT_LATENT_SUB].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_MELT_ENERGY].varname,"OUT_MELT_ENERGY");         /* energy of fusion (melting) [W/m2] */
  out_data[OUT_MELT_ENERGY].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_NET_LONG].varname,"OUT_NET_LONG");               /* net downward longwave flux [W/m2] */
  out_data[OUT_NET_LONG].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_NET_SHORT].varname,"OUT_NET_SHORT");             /* net downward shortwave flux [W/m2] */
  out_data[OUT_NET_SHORT].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_R_NET].varname,"OUT_R_NET");                     /* net downward radiation flux [W/m2] */
  out_data[OUT_R_NET].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_REFREEZE_ENERGY].varname,"OUT_REFREEZE_ENERGY"); /* net energy used to refreeze liquid water in snowpack [W/m2] */
  out_data[OUT_REFREEZE_ENERGY].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SENSIBLE].varname,"OUT_SENSIBLE");               /* net upward sensible heat flux [W/m2] */
  out_data[OUT_SENSIBLE].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SNOW_FLUX].varname,"OUT_SNOW_FLUX");             /* energy flux through snow pack [W/m2] */
  out_data[OUT_SNOW_FLUX].aggtype = AGG_TYPE_AVG;

  // Miscellaneous Terms
  strcpy(out_data[OUT_AERO_RESIST].varname,"OUT_AERO_RESIST");         /* canopy aerodynamic resistance [s/m] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_AERO_COND].varname,"OUT_AERO_COND");             /* canopy aerodynamic conductance [m/s] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_AIR_TEMP].varname,"OUT_AIR_TEMP");               /* air temperature [C] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_DENSITY].varname,"OUT_DENSITY");                 /* near-surface atmospheric density [kg/m3] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_LONGWAVE].varname,"OUT_LONGWAVE");               /* incoming longwave [W/m2] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_PRESSURE].varname,"OUT_PRESSURE");               /* near surface atmospheric pressure [kPa] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_QAIR].varname,"OUT_QAIR");                       /* specific humidity [kg/kg] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_REL_HUMID].varname,"OUT_REL_HUMID");             /* relative humidity [fraction]*/
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SHORTWAVE].varname,"OUT_SHORTWAVE");             /* incoming shortwave [W/m2] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SURF_COND].varname,"OUT_SURF_COND");             /* surface conductance [m/s] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_VP].varname,"OUT_VP");                           /* near surface vapor pressure [kPa] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_WIND].varname,"OUT_WIND");                       /* near surface wind speed [m/s] */
  out_data[OUT_AERO_RESIST].aggtype = AGG_TYPE_AVG;

  // Band-specific quantities
  strcpy(out_data[OUT_ADVECTED_SENSIBLE_BAND].varname,"OUT_ADVECTED_SENSIBLE_BAND"); /* net sensible heat flux advected to snow pack [W/m2] */
  out_data[OUT_ADVECTED_SENSIBLE_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_ADVECTION_BAND].varname,"OUT_ADVECTION_BAND");             /* advected energy [W/m2] */
  out_data[OUT_ADVECTION_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_ALBEDO_BAND].varname,"OUT_ALBEDO_BAND");                   /* albedo [fraction] */
  out_data[OUT_ALBEDO_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_DELTACC_BAND].varname,"OUT_DELTACC_BAND");                 /* change in cold content in snow pack [W/m2] */
  out_data[OUT_DELTACC_BAND].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_GRND_FLUX_BAND].varname,"OUT_GRND_FLUX_BAND");             /* net heat flux into ground [W/m2] */
  out_data[OUT_GRND_FLUX_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_LATENT_BAND].varname,"OUT_LATENT_BAND");                   /* net upward latent heat flux [W/m2] */
  out_data[OUT_LATENT_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_LATENT_SUB_BAND].varname,"OUT_LATENT_SUB_BAND");           /* net upward latent heat flux from sublimation [W/m2] */
  out_data[OUT_LATENT_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_MELT_ENERGY_BAND].varname,"OUT_MELT_ENERGY_BAND");         /* energy of fusion (melting) [W/m2] */
  out_data[OUT_MELT_ENERGY_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_NET_LONG_BAND].varname,"OUT_NET_LONG_BAND");               /* net downward longwave flux [W/m2] */
  out_data[OUT_NET_LONG_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_NET_SHORT_BAND].varname,"OUT_NET_SHORT_BAND");             /* net downward shortwave flux [W/m2] */
  out_data[OUT_NET_SHORT_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_REFREEZE_ENERGY_BAND].varname,"OUT_REFREEZE_ENERGY_BAND"); /* net energy used to refreeze liquid water in snowpack [W/m2] */
  out_data[OUT_REFREEZE_ENERGY_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SENSIBLE_BAND].varname,"OUT_SENSIBLE_BAND");               /* net upward sensible heat flux [W/m2] */
  out_data[OUT_SENSIBLE_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SNOW_CANOPY_BAND].varname,"OUT_SNOW_CANOPY_BAND");         /* snow interception storage in canopy [mm] */
  out_data[OUT_SNOW_CANOPY_BAND].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SNOW_COVER_BAND].varname,"OUT_SNOW_COVER_BAND");           /* fractional area of snow cover [fraction] */
  out_data[OUT_SNOW_COVER_BAND].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SNOW_DEPTH_BAND].varname,"OUT_SNOW_DEPTH_BAND");           /* depth of snow pack [cm] */
  out_data[OUT_SNOW_DEPTH_BAND].aggtype = AGG_TYPE_END;
  strcpy(out_data[OUT_SNOW_FLUX_BAND].varname,"OUT_SNOW_FLUX_BAND");             /* energy flux through snow pack [W/m2] */
  out_data[OUT_SNOW_FLUX_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SNOW_MELT_BAND].varname,"OUT_SNOW_MELT_BAND");             /* snow melt [mm] (ALMA_OUTPUT: [mm/s]) */
  out_data[OUT_SNOW_MELT].aggtype = AGG_TYPE_SUM;
  strcpy(out_data[OUT_SNOW_PACK_TEMP_BAND].varname,"OUT_SNOW_PACK_TEMP_BAND");   /* snow pack temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_SNOW_PACK_TEMP_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SNOW_SURF_TEMP_BAND].varname,"OUT_SNOW_SURF_TEMP_BAND");   /* snow surface temperature [C] (ALMA_OUTPUT: [K]) */
  out_data[OUT_SNOW_SURF_TEMP_BAND].aggtype = AGG_TYPE_AVG;
  strcpy(out_data[OUT_SWE_BAND].varname,"OUT_SWE_BAND");                         /* snow water equivalent in snow pack [mm] */
  out_data[OUT_SWE_BAND].aggtype = AGG_TYPE_END;

  // Set number of elements
  for (v=0; v<N_OUTVAR_TYPES; v++) {
    out_data[v].nelem = 1;
  }
  if (options.FROZEN_SOIL) {
    out_data[OUT_FDEPTH].nelem = MAX_FRONTS;
    out_data[OUT_TDEPTH].nelem = MAX_FRONTS;
  }
  out_data[OUT_SMLIQFRAC].nelem = options.Nlayer;
  out_data[OUT_SMFROZFRAC].nelem = options.Nlayer;
  out_data[OUT_SOIL_ICE].nelem = options.Nlayer;
  out_data[OUT_SOIL_LIQ].nelem = options.Nlayer;
  out_data[OUT_SOIL_MOIST].nelem = options.Nlayer;
  out_data[OUT_SOIL_TEMP].nelem = options.Nlayer;
  out_data[OUT_ADVECTION_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_ALBEDO_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_DELTACC_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_GRND_FLUX_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_LATENT_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_NET_LONG_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_NET_SHORT_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_REFREEZE_ENERGY_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_SENSIBLE_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_SNOW_CANOPY_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_SNOW_COVER_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_SNOW_DEPTH_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_SNOW_FLUX_BAND].nelem = options.SNOW_BAND;
  out_data[OUT_SWE_BAND].nelem = options.SNOW_BAND;

  // Allocate space for data
  for (v=0; v<N_OUTVAR_TYPES; v++) {
    out_data[v].data = (double *)calloc(out_data[v].nelem, sizeof(double));
    out_data[v].aggdata = (double *)calloc(out_data[v].nelem, sizeof(double));
  }

  // Initialize data values
  init_output_list(out_data, FALSE, "%.1f", OUT_TYPE_FLOAT, 1);

  return out_data;

}


void init_output_list(out_data_struct *out_data, int write, char *format, int type, float mult) {
/*************************************************************
  init_output_list()      Ted Bohn     September 08, 2006

  This routine initializes the output information for all output variables.

*************************************************************/
  int varid, i;

  for (varid=0; varid<N_OUTVAR_TYPES; varid++) {
    out_data[varid].write = write;
    strcpy(out_data[varid].format,format);
    out_data[varid].type = type;
    out_data[varid].mult = mult;
    for(i=0; i<out_data[varid].nelem; i++) {
      out_data[varid].data[i] = 0;
    }
  }

}


int set_output_var(out_data_file_struct *out_data_files,
                    int write,
                    int filenum,
                    out_data_struct *out_data,
                    char *varname,
                    int varnum,
                    char *format,
                    int type,
                    float mult) {
/*************************************************************
  set_output_var()      Ted Bohn     September 08, 2006

  This routine updates the output information for a given output variable.

*************************************************************/
  int varid;
  int found=FALSE;
  int status=0;

  for (varid=0; varid<N_OUTVAR_TYPES; varid++) {
    if (strcmp(out_data[varid].varname,varname) == 0) {
      found = TRUE;
      out_data[varid].write = write;
      if (strcmp(format,"*") != 0)
        strcpy(out_data[varid].format,format);
      if (type != 0)
        out_data[varid].type = type;
      if (mult != 0)
        out_data[varid].mult = mult;
      out_data_files[filenum].varid[varnum] = varid;
    }
  }
  if (!found) {
    status = -1;
    fprintf(stderr, "Error: set_output_var: \"%s\" was not found in the list of supported output variable names.  Please use the exact name listed in vicNl_def.h.\n", varname);
  }
  return status;

}


void zero_output_list(out_data_struct *out_data) {
/*************************************************************
  zero_output_list()      Ted Bohn     September 08, 2006

  This routine resets the values of all output variables to 0.

*************************************************************/
  int varid, i;

  for (varid=0; varid<N_OUTVAR_TYPES; varid++) {
    for(i=0; i<out_data[varid].nelem; i++) {
      out_data[varid].data[i] = 0;
    }
  }

}

void free_out_data_files(out_data_file_struct **out_data_files) {
/*************************************************************
  free_out_data_files()      Ted Bohn     September 08, 2006

  This routine frees the memory in the out_data_files array.

*************************************************************/
  extern option_struct options;
  int filenum;

  for (filenum=0; filenum<options.Noutfiles; filenum++) {
    free((char*)(*out_data_files)[filenum].varid);
  }
  free((char*)(*out_data_files));

}
