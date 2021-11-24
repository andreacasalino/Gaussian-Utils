if(EIGEN_INSTALL_FOLDER)
	add_subdirectory(${EIGEN_INSTALL_FOLDER})
else()
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
