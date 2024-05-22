import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Home from './pages/home';
import Video from './pages/video';
import Header from './components/header';

function App() {
  return (
    <div>
      <Router>
        <Header />
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/video/:id" element={<Video />} />
        </Routes>
      </Router>
    </div>
  );
}

export default App;
