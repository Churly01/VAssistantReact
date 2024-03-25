const { ipcRenderer } = require('electron');

ipcRenderer.on('frame', (event, buffer_image) => {
  const frameURL = `data:image/jpeg;base64,${Buffer.from(buffer_image).toString('base64')}`;
  document.getElementById('frame').src = frameURL;
});
