#ifndef GnssCenter_APP_H
#define GnssCenter_APP_H

#include <QtGui>

class t_app : public QApplication {
 Q_OBJECT
 public:
  t_app(int& argc, char* argv[], bool GUIenabled);
  virtual ~t_app();
 protected:
  virtual bool event(QEvent* ev);
 private:
};

#endif

