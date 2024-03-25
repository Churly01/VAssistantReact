import WeatherGadget from "./components/WeatherGadget";

const MainSelection = () => {

  // Display grid of 2 rows and 2 columns
  // Add cool animation for the buttons to seem dynamic

  return (
    // Second row occupies the full width
    <div className="flex flex-col gap-5 w-full ">
      <div className="flex gap-5 flex-[2] max-h-full overflow-hidden">
        <div className='flex-1'>
          <img
            id="frame"
            alt="Frame"
            className="w-full h-full object-cover"
          />
        </div>
        <button className="flex-1 bg-blue-500 text-white p-4 rounded-lg">
          Chatgpt
        </button>
      </div>
      <div className="flex-1 text-white p-4 rounded-lg">
        <WeatherGadget />
      </div>
    </div>
  );
};


const MainScreen = () => {
  return (
    <main className="flex min-h-full max-h-full flex-col items-center gap-5">
      <h1 className="text-4xl font-bold">Bienvenido a tu asistente</h1>
      <p className="text-lg text-center">
        Aquí podrás encontrar información sobre tus tareas, recordatorios y
        eventos.
      </p>
      <div className="flex flex-1 overflow-hidden w-11/12">
        <MainSelection />
      </div>
    </main>
  )
}
export default MainScreen;
