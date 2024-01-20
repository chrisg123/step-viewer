#ifndef STAIRCASEVIEWER_HPP
#define STAIRCASEVIEWER_HPP
#include "AppContext.hpp"
#include "GraphicsUtilities.hpp"
#include <memory>
#include <optional>
#include <string>
#include <mutex>
class StaircaseViewer {
public:
  StaircaseViewer(std::string const &containerId);

  void createCanvas(std::string containerId, std::string canvasId);
  void displaySplashScreen();
  std::string getDemoStepFile();
  std::string getOCCTVersion();
  void initEmptyScene();
  ~StaircaseViewer();

  std::shared_ptr<AppContext> context;

  int loadStepFile(std::string const &stepFileContent);
  static void handleMessages(void *arg);

  static void* backgroundWorker(void *arg);
  void setStepFileContent(const std::string& content);
  std::string getStepFileContent();
  void fitAllObjects ();
private:
  pthread_t backgroundWorkerThread;
  bool backgroundWorkerRunning = false;

  std::string _stepFileContent;
  std::mutex stepFileContentMutex;

  static void* _loadStepFile(void *args);
};

extern "C" void dummyMainLoop();
void dummyDeleter(StaircaseViewer *);

inline bool arePthreadsEnabled() {
#ifdef __EMSCRIPTEN_PTHREADS__
  return true;
#else
  return false;
#endif
}

#endif // STAIRCASEVIEWER_HPP
