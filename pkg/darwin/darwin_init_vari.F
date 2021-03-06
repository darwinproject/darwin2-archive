C $Header: /u/gcmpack/MITgcm_contrib/darwin2/pkg/darwin/darwin_init_vari.F,v 1.7 2013/12/04 21:27:54 jahn Exp $
C $Name:  $

#include "DARWIN_OPTIONS.h"

C !INTERFACE: ==========================================================
      SUBROUTINE DARWIN_INIT_VARI(myThid )

C !DESCRIPTION:
C calls subroutines that initialize any time dependent variables
C for any tracer experiment

C !USES: ===============================================================
      IMPLICIT NONE

#include "SIZE.h"
#include "EEPARAMS.h"
#include "DARWIN_SIZE.h"
#include "DARWIN_IO.h"

C !INPUT PARAMETERS: ===================================================
C  myThid               :: thread number
      INTEGER myThid
CEOP

#ifdef ALLOW_DARWIN

C !FUNCTIONS: ==========================================================
      LOGICAL MASTER_CPU_THREAD
      EXTERNAL MASTER_CPU_THREAD

C !LOCAL VARIABLES: ====================================================
      INTEGER i,j,bi,bj

c set up ecosystem coefficients
c
c seed randomization
      _BEGIN_MASTER( myThid )
      CALL DARWIN_RANDOM_INIT(darwin_seed, myThid)
      _END_MASTER( myThid )
      _BARRIER

      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
           FIce(i,j,bi,bj) = 0. _d 0
         ENDDO
        ENDDO
       ENDDO
      ENDDO

#ifdef ALLOW_QUOTA
      call QUOTA_INIT_VARI(myThid )
#endif

#ifdef ALLOW_MONOD
      call MONOD_INIT_VARI(myThid )
#endif

#ifdef CALC_RATE_TOTALS
c find unused units for darwin_rate output
      IF (MASTER_CPU_THREAD(myThid)) THEN
       CALL MDSFINDUNIT( DAR_ratetot_unit, mythid )
       open(DAR_ratetot_unit,file='darwin_ratetot.txt',status='unknown')
#ifdef ALLOW_CARBON
       CALL MDSFINDUNIT( DAR_fluxtot_unit, mythid )
       open(DAR_fluxtot_unit,file='darwin_fluxtot.txt',status='unknown')
#endif
      ENDIF
#endif

#endif /* ALLOW_DARWIN */

      RETURN
      END
