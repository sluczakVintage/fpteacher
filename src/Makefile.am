bin_PROGRAMS = fpteacher

# set the include path found by configure
AM_CPPFLAGS =  $(LIBSDL_CFLAGS) $(all_includes)

# the library search path.
fpteacher_LDFLAGS = $(all_libraries) $(LIBSDL_RPATH)
fpteacher_LDADD = $(LIBSDL_LIBS)
fpteacher_SOURCES = CAnimation.cpp CAnimationMgr.cpp CAnimator.cpp \
	CAudioSystem.cpp CAuditorium.cpp CDynamicEntity.cpp CEngine.cpp CEntity.cpp CField.cpp \
	CGui.cpp CInput.cpp CMouseEvent.cpp CMouseObserver.cpp CMusic.cpp CNetwork.cpp \
	CNetworkEvent.cpp COGLWindow.cpp CSound.cpp CSoundNetworkEvent.cpp CSprite.cpp \
	CSpriteMgr.cpp CStaticEntity.cpp CStudentNetworkEvent.cpp CTimer.cpp \
	CTimerObserver.cpp CVideoSystem.cpp CWorld.cpp fpteacher.cpp utils.cpp
