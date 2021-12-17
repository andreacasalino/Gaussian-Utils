set(EigenName_To_Link Eigen3::Eigen)

if(EIGEN_INSTALL_FOLDER)
	message(STATUS "linking Eigen at folder ${EIGEN_INSTALL_FOLDER}")
	add_library(Eigen3_Shell INTERFACE)
	
	target_include_directories(Eigen3_Shell INTERFACE
		${EIGEN_INSTALL_FOLDER}
	)
	set(EigenName_To_Link Eigen3_Shell)	
else()
	message(STATUS "fetching Eigen")
	include(FetchContent)
	FetchContent_Declare(
	  eigen
	  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	  GIT_TAG        b3bea43a2da484d420e20c615cb5c9e3c04024e5
	)
	FetchContent_MakeAvailable(eigen)
endif()

set(PROJECT_SHORTNAME GaussianUtils)

MakeLibrary(${PROJECT_SHORTNAME} header)

target_link_libraries(${PROJECT_SHORTNAME} PUBLIC
${EigenName_To_Link}
)

