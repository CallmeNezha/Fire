TEMPLATE = subdirs
SUBDIRS = fire \
          examples/statusbar


# SUBDIRS = lib unit-test app # app not ready
# app.depends = lib # may exclude dependcies
columnbar.depends = lib
statusbar.depends = lib
