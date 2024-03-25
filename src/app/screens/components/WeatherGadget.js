import ReactWeather, { useOpenWeather } from 'react-open-weather';

const WeatherGadget = () => {
  const { data, isLoading, errorMessage } = useOpenWeather({
    key: 'a827d725f8162f710b61f16975fe7986',
    lat: '40.490631',
    lon: '-3.964320',
    lang: 'es',
    unit: 'metric', // values are (metric, standard, imperial)
  });
  return (
    <ReactWeather
      isLoading={isLoading}
      errorMessage={errorMessage}
      data={data}
      lang="es"
      locationLabel="Villanueva del Pardillo"
      unitsLabels={{ temperature: 'C', windSpeed: 'Km/h' }}
      showForecast={false}
    />
  );
};
export default WeatherGadget;
