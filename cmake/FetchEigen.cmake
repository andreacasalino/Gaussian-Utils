function(FETCH_EIGEN)

if (TARGET Eigen3::Eigen)
  return()
endif()
if (TARGET EigenIntrfc)
  return()
endif()

if(EIGEN_INSTALL_FOLDER)
	message(STATUS "using Eigen from local folder at ${EIGEN_INSTALL_FOLDER}")
	
	add_library(EigenIntrfc INTERFACE)

	target_include_directories(EigenIntrfc INTERFACE ${EIGEN_INSTALL_FOLDER})	
else()	
	message(STATUS "fetching Eigen from git")

	include(FetchContent)
	FetchContent_Declare(
	  eigen
	  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	  GIT_TAG        b3bea43a2da484d420e20c615cb5c9e3c04024e5
	)
	FetchContent_MakeAvailable(eigen)
endif()

endfunction()


function(LINK_EIGEN TARGET_NAME)

if (TARGET EigenIntrfc)
	target_link_libraries(${TARGET_NAME} INTERFACE EigenIntrfc)
	return()
endif()

if (TARGET Eigen3::Eigen)
	target_link_libraries(${TARGET_NAME} PUBLIC Eigen3::Eigen)
	return()
endif()

endfunction()
