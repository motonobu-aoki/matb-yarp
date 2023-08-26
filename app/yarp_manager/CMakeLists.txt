 
 set( appname matbApp )
file( GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini )
file( GLOB scripts *.xml )
# Removed the installation in $ICUB_ROOT/app 11/10/13
#icub_app_install(${appname}
#                 FILES ${conf}
#                 DESTINATION conf)
#icub_app_install(${appname}
#                FILES ${scripts}
#                DESTINATION scripts)
yarp_install( FILES ${conf} DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname} )
# yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_TEMPLATES_INSTALL_DIR})
install( FILES ${scripts} DESTINATION share/ICUBcontrib/applications )
 
