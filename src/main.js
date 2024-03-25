const { app, BrowserWindow, session } = require('electron');
const { spawn } = require('child_process');

app.commandLine.appendSwitch('disable-http-cache');

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  app.quit();
}

// <meta charset="utf-8" content="img-src 'self' blob: data:;" />

const createWindow = () => {
  let frame = Buffer.alloc(0);
  let frameSize = 0;

  const cpprocess = spawn(`${FACE_RECOG_PATH}/main`, [`${FACE_RECOG_PATH}`]);
  cpprocess.on('exit', (code) => {
    console.log(`Child process exited with code ${code}`);
  });
  cpprocess.on('error', (err) => {
    console.log('Failed to start subprocess.', err);
  });
  cpprocess.stderr.on('data', (data) => {
    console.error(`stderr: ${data}`);
  });
  cpprocess.stdout.on('data', (data) => {
    // First receive size of the frame
    if (frameSize === 0) {
      frameSize = data.readUInt32LE(0);
      console.log('Frame size:', frameSize);
      frame = Buffer.from(data.slice(4));
      frameSize -= (data.length - 4);
    }
    else {
      frame = Buffer.concat([frame, data]);
      frameSize -= data.length;
    }

    if (frameSize <= 0) {

      // Send it
      mainWindow.webContents.send('frame', Buffer.from(frame));
      // Respond to the cpprocess
      frameSize = 0;
      frame = Buffer.alloc(0);
      cpprocess.stdin.write('a');
    }
  });

  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY,
    },
  });

  // and load the index.html of the app.
  mainWindow.loadURL(MAIN_WINDOW_WEBPACK_ENTRY);

  // Open the DevTools.
  mainWindow.webContents.openDevTools();
};

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(() => {

  session.defaultSession.webRequest.onHeadersReceived((details, callback) => {
    callback({
      responseHeaders: {
        ...details.responseHeaders,
        'Content-Security-Policy': ['img-src \'self\' blob: data:']
      }
    })
  })
  createWindow();

  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and import them here.
