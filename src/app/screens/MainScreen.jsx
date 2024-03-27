import WeatherGadget from "./components/WeatherGadget";
import OpenAiPrompt from "./components/OpenAiPrompt";

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
            className="w-full h-full object-cover border-2 border-gray-300 rounded-lg"
          />
        </div>
        <div className='flex-1 border-2 border-gray-300 rounded-lg p-5 h-full overflow-hidden'>
          <OpenAiPrompt />
        </div>
      </div>
    </div>
  );
};


const MainScreen = () => {
  return (
    <main className="flex min-h-full max-h-full flex-col items-center gap-5">
      <div className="flex flex-1 overflow-hidden w-11/12">
        <MainSelection />
      </div>
    </main>
  )
}
export default MainScreen;
