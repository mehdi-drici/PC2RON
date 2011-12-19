#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/serveur.o \
	${OBJECTDIR}/trame.o \
	${OBJECTDIR}/reception.o \
	${OBJECTDIR}/factory.o \
	${OBJECTDIR}/envoi.o \
	${OBJECTDIR}/joueur.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/builder.o \
	${OBJECTDIR}/protocole.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=-ansi -O2 -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Wconversion -Wsign-compare -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Winline -Wlong-long -Wunreachable-code

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pc2ron_serveur

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pc2ron_serveur: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pc2ron_serveur ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/serveur.o: serveur.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/serveur.o serveur.c

${OBJECTDIR}/trame.o: trame.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/trame.o trame.c

${OBJECTDIR}/reception.o: reception.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/reception.o reception.c

${OBJECTDIR}/factory.o: factory.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/factory.o factory.c

${OBJECTDIR}/envoi.o: envoi.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/envoi.o envoi.c

${OBJECTDIR}/joueur.o: joueur.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/joueur.o joueur.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/builder.o: builder.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/builder.o builder.c

${OBJECTDIR}/protocole.o: protocole.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Werror -MMD -MP -MF $@.d -o ${OBJECTDIR}/protocole.o protocole.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${OBJECTDIR}/serveur_nomain.o: ${OBJECTDIR}/serveur.o serveur.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/serveur.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/serveur_nomain.o serveur.c;\
	else  \
	    ${CP} ${OBJECTDIR}/serveur.o ${OBJECTDIR}/serveur_nomain.o;\
	fi

${OBJECTDIR}/trame_nomain.o: ${OBJECTDIR}/trame.o trame.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/trame.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/trame_nomain.o trame.c;\
	else  \
	    ${CP} ${OBJECTDIR}/trame.o ${OBJECTDIR}/trame_nomain.o;\
	fi

${OBJECTDIR}/reception_nomain.o: ${OBJECTDIR}/reception.o reception.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/reception.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/reception_nomain.o reception.c;\
	else  \
	    ${CP} ${OBJECTDIR}/reception.o ${OBJECTDIR}/reception_nomain.o;\
	fi

${OBJECTDIR}/factory_nomain.o: ${OBJECTDIR}/factory.o factory.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/factory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/factory_nomain.o factory.c;\
	else  \
	    ${CP} ${OBJECTDIR}/factory.o ${OBJECTDIR}/factory_nomain.o;\
	fi

${OBJECTDIR}/envoi_nomain.o: ${OBJECTDIR}/envoi.o envoi.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/envoi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/envoi_nomain.o envoi.c;\
	else  \
	    ${CP} ${OBJECTDIR}/envoi.o ${OBJECTDIR}/envoi_nomain.o;\
	fi

${OBJECTDIR}/joueur_nomain.o: ${OBJECTDIR}/joueur.o joueur.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/joueur.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/joueur_nomain.o joueur.c;\
	else  \
	    ${CP} ${OBJECTDIR}/joueur.o ${OBJECTDIR}/joueur_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/builder_nomain.o: ${OBJECTDIR}/builder.o builder.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/builder.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/builder_nomain.o builder.c;\
	else  \
	    ${CP} ${OBJECTDIR}/builder.o ${OBJECTDIR}/builder_nomain.o;\
	fi

${OBJECTDIR}/protocole_nomain.o: ${OBJECTDIR}/protocole.o protocole.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocole.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.c) -g -Werror -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/protocole_nomain.o protocole.c;\
	else  \
	    ${CP} ${OBJECTDIR}/protocole.o ${OBJECTDIR}/protocole_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pc2ron_serveur

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
