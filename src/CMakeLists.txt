set(EIGEN_INSTALL_FOLDER "C:\Users\andre\Desktop\jashjfas\eigen\")

if(EIGEN_INSTALL_FOLDER)
	# message(STATUS "linking Eigen at folder ${EIGEN_INSTALL_FOLDER}")
	add_library(Eigen3::Eigen INTERFACE )
	
	target_include_directories(Eigen3::Eigen INTERFACE
		${EIGEN_INSTALL_FOLDER}
	)	
else()
	# message(STATUS "fetching Eigen")
	include(FetchContent)
	FetchContent_Declare(
	  eigen
	  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	  GIT_TAG        master
	)
	FetchContent_MakeAvailable(eigen)
endif()

set(PROJECT_SHORTNAME GaussianUtils)

MakeLibrary(${PROJECT_SHORTNAME} header)

target_link_libraries(${PROJECT_SHORTNAME} PUBLIC
Eigen3::Eigen
)
