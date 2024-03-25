import { createRoot } from 'react-dom/client';
import './index.css';
import App from './app/index.jsx';
import {
  createHashRouter,
  RouterProvider,

} from "react-router-dom";


const router = createHashRouter([
  {
    path: "/",
    element: <App />,
  }, // Redirect everything to the root component
]);

const root = createRoot(document.body);
root.render(
  <RouterProvider router={router} />
);
