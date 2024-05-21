import { useState } from 'react'
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'
import Home from "./pages/home"


function App() {


  return (
    <>
      <div className='bg-black m-0 p-10'>
        <Router >
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/about" element={<p>about</p>} />

          </Routes>

        </Router>
      </div>
    </>
  )
}

export default App
