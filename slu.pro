TEMPLATE = subdirs
SUBDIRS = fire \
          examples/tableview \
          examples/columnbar \
          examples/statusbar



# SUBDIRS = lib unit-test app # app not ready
# app.depends = lib # may exclude dependcies
columnbar.depends = fire
statusbar.depends = fire
tableview.depends = fire
