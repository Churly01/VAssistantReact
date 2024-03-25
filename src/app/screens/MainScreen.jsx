import { useState } from 'react';

const MainSelection = () => {

  // Display grid of 2 rows and 2 columns
  // Add cool animation for the buttons to seem dynamic

  return (
    <div className="grid grid-cols-2 grid-rows-2 gap-4 w-full">
      <button
        className="flex-1 bg-blue-500 text-white p-4 rounded-lg"
      >
        Hola USUARIO
      </button>
      <button className="flex-1 bg-blue-500 text-white p-4 rounded-lg">
        Chatgpt
      </button>
      <img
        id="frame"
        alt="Frame" />
      <button className="flex-1 bg-blue-500 text-white p-4 rounded-lg">
        Clima
      </button>
      <button className="flex-1 bg-blue-500 text-white p-4 rounded-lg">
        Wifi
      </button>
    </div>
  );
};


const MainScreen = () => {
  return (
    <main className="flex min-h-full flex-col items-center p-10 gap-5 w-full">
      <h1 className="text-4xl font-bold">Bienvenido a tu asistente</h1>
      <p className="text-lg text-center">
        Aquí podrás encontrar información sobre tus tareas, recordatorios y
        eventos.
      </p>
      <div className="w-full flex flex-1">
        <MainSelection />
      </div>
    </main>
  )
}
export default MainScreen;
