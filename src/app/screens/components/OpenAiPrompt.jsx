import { useState, useMemo } from 'react';
import LlamaAI from 'llamaai';

const llamaAPI = new LlamaAI('LL-hZR6CD2nKfVE9x9Sx9EnS8g971RuZDfVBheylZZgKZz6tD04cc4azyRSWSyFutGN');


const OpenAiPrompt = () => {

  const [prompt, setPrompt] = useState('What is the capital of France?');
  const [response, setResponse] = useState('');
  const [ isLoading, setIsLoading ] = useState(false);

  const apiRequestJson = useMemo(() => {
    return {
      messages: [{ role: "user", content: prompt }],
      stream: false,
    };
  }, [prompt]);
  return (
    <div>
      <input
        value={prompt}
        onChange={(e) => setPrompt(e.target.value)}
        className="text-black p-2 border border-gray-300 rounded-lg w-full"
      />
      <button
        onClick={() => {
          setResponse('Loading...');
          llamaAPI.run(apiRequestJson).then((response) => {
            setResponse(response.choices[0].message.content);
          }).catch((error) => {
            console.error(error)
          });
        }}
        disabled={isLoading}
      >
        Submit
      </button>
      <p>{response}</p>
    </div>
  );
}

export default OpenAiPrompt;
