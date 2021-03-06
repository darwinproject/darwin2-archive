C $Header: /u/gcmpack/MITgcm_contrib/darwin2/pkg/darwin/DARWIN_IO.h,v 1.10 2015/05/19 14:30:15 benw Exp $
C $Name:  $

#include "DARWIN_OPTIONS.h"

c DARWIN_IO.h
c --------------------------------------------------------------------
c  Description:  input and diagnostic output for DARWIN pkg
c          Stephanie Dutkiewicz: Spring 2006
c NOTE: additional diagnostics still needed
c --------------------------------------------------------------------      

C--   COMMON /DARWIN_FILENAMES/
C  darwin_iceFile       :: file name of seaice fraction
C  darwin_ironFile      :: file name of aeolian iron flux
C  darwin_PARFile       :: file name of Photosynthetically Active Radiation at surface
C  darwin_nutWVelFile   :: file name of nutrient wvel
C  darwin_waterabsorbFile    :: file name of water absorption/scattering spectra
C  darwin_phytoabsorbFile    :: file name of phyto absorption/scattering spectra
C  darwin_particleabsorbFile :: file name of particle absorption/scattering spectra
C  darwin_surfacespecFile    :: file name of spectrum of incident light
C  darwin_acdomFile          :: file name of CDOM absorption spectrum
C  darwin_PARunits      :: units of data in PAR file; one of Ein/m2/d, uEin/m2/s, W/m2
C  darwin_PARFileConv   :: conversion factor from PAR file units to uEin/m2/s
C  darwin_W_to_uEins    :: conversion factor from W to uEin/s
C  darwin_ironUnits     :: units of data in iron file; one of mol Fe/m2/s, kg dust/m2/s
C  darwin_dustFrac      :: fraction of dust by weight that is iron
C  darwin_forcingPeriod :: perioDARWIN forcing parameter specific for DARWIN (seconds)
C  darwin_forcingCycle  :: perioDARWIN forcing parameter specific for DARWIN (seconds)
C  darwin_seed          :: seed for the random number generator

      COMMON /DARWIN_FILENAMES/
     &        darwin_iceFile,
     &        darwin_ironFile,
     &        darwin_PARFile,
     &        darwin_nutWVelFile,
     &        darwin_PO4_relaxFile, darwin_NO3_relaxFile,
     &        darwin_FeT_relaxFile, darwin_Si_relaxFile,
     &        darwin_relaxscale,
     &        darwin_PO4_fluxFile, darwin_NO3_FluxFile,
     &        darwin_FeT_fluxFile, darwin_Si_fluxFile,
     &        darwin_oasim_edFile, darwin_oasim_esFile,
     &        darwin_waterabsorbFile, darwin_phytoabsorbFile,
     &        darwin_surfacespecFile, darwin_acdomFile,
     &        darwin_particleabsorbFile,
     &        darwin_PARunits, darwin_ironUnits,
     &        darwin_PARFileConv, darwin_ironFileConv,
     &        darwin_dustFrac,
     &        darwin_W_to_uEins,
     &        darwin_forcingPeriod, darwin_forcingCycle,
     &        darwin_seed

      CHARACTER*(MAX_LEN_FNAM) darwin_iceFile
      CHARACTER*(MAX_LEN_FNAM) darwin_ironFile
      CHARACTER*(MAX_LEN_FNAM) darwin_PARFile
      CHARACTER*(MAX_LEN_FNAM) darwin_NutWVelFile
      CHARACTER*(MAX_LEN_FNAM) darwin_PO4_relaxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_NO3_relaxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_FeT_relaxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_Si_relaxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_PO4_fluxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_NO3_fluxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_FeT_fluxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_Si_fluxFile
      CHARACTER*(MAX_LEN_FNAM) darwin_oasim_edFile
      CHARACTER*(MAX_LEN_FNAM) darwin_oasim_esFile
      CHARACTER*(MAX_LEN_FNAM) darwin_waterabsorbFile
      CHARACTER*(MAX_LEN_FNAM) darwin_phytoabsorbFile
      CHARACTER*(MAX_LEN_FNAM) darwin_particleabsorbFile
      CHARACTER*(MAX_LEN_FNAM) darwin_surfacespecFile
      CHARACTER*(MAX_LEN_FNAM) darwin_acdomFile
      CHARACTER*(MAX_LEN_FNAM) darwin_PARunits
      CHARACTER*(MAX_LEN_FNAM) darwin_ironUnits

      _RL darwin_relaxscale
      _RL     darwin_forcingPeriod
      _RL     darwin_forcingCycle
      _RL darwin_PARFileConv
      _RL darwin_W_to_uEins
      _RL darwin_ironFileConv
      _RL darwin_dustFrac
      INTEGER darwin_seed

      COMMON/DARWIN_IO_L/
     &  darwin_useiceFile,
     &  darwin_useareamask,
     &  darwin_useiceMask,
     &  darwin_useAREA,
     &  darwin_haveIce
      LOGICAL darwin_useiceFile
      LOGICAL darwin_useareamask
      LOGICAL darwin_useiceMask
      LOGICAL darwin_useAREA
      LOGICAL darwin_haveIce

c INPUT:
c    fice           - ice fraction
c    inputFe        - aeolian input of iron
c    sur_par        - surface PAR
      COMMON /DARWIN_INPUT/
     &       fice, inputFe, sur_par
#ifdef NUT_SUPPLY
     &      ,nut_wvel
#endif
#ifdef RELAX_NUTS
     &      ,po4_obs, no3_obs, fet_obs, si_obs
#endif
#ifdef FLUX_NUTS
     &      ,po4_flx, no3_flx, fet_flx, si_flx
#endif
c
       _RL   fice(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx, nSy)
       _RL   inputFe(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx, nSy)
       _RL   sur_par(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx, nSy)
#ifdef NUT_SUPPLY
       _RL   nut_wvel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
#endif
#ifdef RELAX_NUTS
       _RL   po4_obs(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL   no3_obs(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL   fet_obs(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL   si_obs(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
#endif
#ifdef FLUX_NUTS
       _RL   po4_flx(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL   no3_flx(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL   fet_flx(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL   si_flx(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
#endif
c
c OUPUT DIAGNOSTICS
c    PPave        - average primary production
c    Nfixave      - average N fixation
c    Zoograzave   - average zooplankton consumption
c    Parave       - average PAR
c    Chlave       - average chlorophyll
c    npzd_timeave - time for averaging
c    Nlim,Flim,etc- Quota model average limitation factors

      COMMON /DARWIN_OUPUT/
     &      PPave, Nfixave, Zoograzave,
     &      PARave, Chlave, Denitave, 
#ifdef QUOTA_DIAG_LIMIT 
     &      Tlimave,
     &      Ilimave,AP_C_ave,HP_C_ave,
     &      Nlimave,AP_N_ave,HP_N_ave,
#ifdef PQUOTA
     &      Plimave,AP_P_ave,HP_P_ave,
#endif
#ifdef FQUOTA
     &      Flimave,AP_F_ave,HP_F_ave,
#endif
#endif
c ANNA_TAVE
#ifdef WAVES_DIAG_PCHL
     &      Pchlave,
#endif
#ifdef DAR_DIAG_ACDOM
     &      aCDOMave,
#endif
#ifdef DAR_DIAG_PARW
     &      chl2cave,
#endif
#ifdef DAR_DIAG_EK
     &      Ekave, EkoverEave, acclimave,
#endif
c ANNA end TAVE
#ifdef DAR_DIAG_RSTAR
     &      Rstarave, RNstarave,
#endif
#ifdef DAR_DIAG_DIVER
     &      Diver1ave, Diver2ave, Diver3ave, Diver4ave,
#endif
#ifdef DAR_DIAG_GROW
     &      Growave, Growsqave,
#endif
#ifdef ALLOW_DIAZ
#ifdef DAR_DIAG_NFIXP
     &      NfixPave,
#endif
#endif
     &      dar_timeave
c  
       _RL  PPave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Nfixave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Zoograzave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  PARave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Chlave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Denitave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
#ifdef QUOTA_DIAG_LIMIT
c Carbon
       _RL  AP_C_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  HP_C_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
c Nitrogen
       _RL  AP_N_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  HP_N_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  Nlimave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
c Phosphorus
#ifdef PQUOTA
       _RL  AP_P_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  HP_P_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  Plimave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
#endif
c Iron
#ifdef FQUOTA
       _RL  AP_F_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  HP_F_ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
       _RL  Flimave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
#endif
c Light
       _RL  Ilimave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,npmax)
c Temperature
       _RL  Tlimave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy)
#endif
c ANNA_TAVE
#ifdef WAVES_DIAG_PCHL
       _RL  Pchlave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
#endif
#ifdef DAR_DIAG_ACDOM
       _RL  aCDOMave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy)
#endif
#ifdef DAR_DIAG_PARW
       _RL  chl2cave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
#endif
#ifdef DAR_DIAG_EK
       _RL  Ekave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
       _RL  EkoverEave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
       _RL  acclimave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
#endif
c ANNA end TAVE
#ifdef DAR_DIAG_RSTAR
       _RL  Rstarave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
       _RL  RNstarave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
#endif
#ifdef DAR_DIAG_DIVER
       _RL  Diver1ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Diver2ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Diver3ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
       _RL  Diver4ave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy)
#endif
#ifdef DAR_DIAG_GROW
       _RL Growave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
       _RL Growsqave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
#endif
#ifdef ALLOW_DIAZ
#ifdef DAR_DIAG_NFIXP
       _RL  NfixPave(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx, nSy,npmax)
#endif
#endif
       _RL  DAR_timeave(nSx,nSy)

#ifdef CHECK_CONS
      COMMON /DARWIN_CHECK_CONS/
     &      DAR_cons_unitC, DAR_cons_unitN,
     &      DAR_cons_unitP, DAR_cons_unitF,
     &      DAR_cons_unitS, DAR_cons_unitA,
     &      DAR_cons_unitO
       INTEGER DAR_cons_unitC
       INTEGER DAR_cons_unitN
       INTEGER DAR_cons_unitP
       INTEGER DAR_cons_unitF
       INTEGER DAR_cons_unitS
       INTEGER DAR_cons_unitA
       INTEGER DAR_cons_unitO
#endif

#ifdef CALC_RATE_TOTALS
      COMMON /DARWIN_RATE_TOT/
     &      DAR_ratetot_unit, DAR_fluxtot_unit
       INTEGER DAR_ratetot_unit
       INTEGER DAR_fluxtot_unit
#endif

#ifdef ALLOW_PAR_DAY
C     PARday    :: array for accumulating/storing daily-averaged PAR
      COMMON /DARWIN_PAR_DAY/ PARday,
     &      darwin_PARavPeriod, darwin_PARnav
      _RL PARday(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nR,nSx,nSy,2)
      _RL darwin_PARavPeriod
      INTEGER darwin_PARnav
#endif

#ifdef ALLOW_CARBON
C--   COMMON /DIC_FILENAMES/
C  DIC_windFile    :: file name of wind speeds
C  DIC_atmospFile  :: file name of atmospheric pressure
C  dic_pCO2          :: Atmospheric pCO2 to be rad in data.dic
C  dic_int*          :: place holder to read in a integer number, set at run time

      COMMON /DIC_FILENAMES/
     &        DIC_windFile, DIC_atmospFile, 
     &        dic_pCO2, dic_int1, dic_int2, dic_int3, dic_int4
      CHARACTER*(MAX_LEN_FNAM) DIC_windFile
      CHARACTER*(MAX_LEN_FNAM) DIC_atmospFile
      _RL dic_pCO2
      INTEGER dic_int1
      INTEGER dic_int2
      INTEGER dic_int3
      INTEGER dic_int4
#endif

