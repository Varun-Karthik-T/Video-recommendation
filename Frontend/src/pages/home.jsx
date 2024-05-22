import React from 'react';
import { useNavigate } from 'react-router-dom';

export default function Home() {
    const navigate = useNavigate();
    const thumbnails = new Array(9).fill('https://picsum.photos/200/200');

    const handleVideoClick = (id) => {
        console.log("handle video", id);
        navigate(`/video/${id}`);
    };

    return (
        <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-6 mt-10 mx-12 mb-10">
            {thumbnails.map((thumbnail, index) => (
                <div 
                    key={index} 
                    onClick={() => handleVideoClick(index)} 
                    className="relative cursor-pointer group"
                >
                    <img
                        className="w-full h-[14.5rem] object-cover rounded-lg"
                        src={thumbnail}
                        alt={`Thumbnail ${index + 1}`}
                    />
                    <div className="p-4 bg-gray-900 text-white absolute bottom-0 left-0 right-0 opacity-75 group-hover:opacity-100 transition-opacity duration-300">
                        <div className="font-bold text-lg">Card title {index + 1}</div>
                    </div>
                </div>
            ))}
        </div>
    );
}
