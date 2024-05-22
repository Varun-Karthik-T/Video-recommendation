import React from 'react';
import { useParams } from 'react-router-dom';

export default function Video() {
    const { id } = useParams();
    console.log("inside video", id);

    const sample = {
        title: "Card title 1",
        description: "This is a description for card 1",
        videolink: "https://www.youtube.com/embed/Aoc0izYJJ8E" // Correct YouTube embed URL format
    };
    const thumbnails = new Array(6).fill('https://picsum.photos/200/200');
    return (
        <div className="flex flex-col items-center justify-center mt-10 w-full px-4">
            <div className="w-full max-w-4xl">
                <div className="aspect-w-16 aspect-h-9">
                    <iframe 
                        src={sample.videolink} 
                        title="video player" 
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" 
                        allowFullScreen
                        className="w-full h-full"
                    ></iframe>
                </div>
                <h1 className="text-4xl font-bold mt-4 mb-2">{sample.title}</h1>
                <p className="text-lg">{sample.description}</p>
            </div>
            <div className='mb-10'>
                <h2 className="text-2xl font-bold mt-8">More videos</h2>
                <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-6 mt-4">
                    {thumbnails.map((thumbnail, index) => (
                        <div key={index} className="relative cursor-pointer group">
                            <img
                                className="w-full h-48 object-cover rounded-lg"
                                src={thumbnail}
                                alt={`Thumbnail ${index + 1}`}
                            />
                            <div className="p-4 bg-gray-900 text-white absolute bottom-0 left-0 right-0 opacity-75 group-hover:opacity-100 transition-opacity duration-300">
                                <div className="font-bold text-lg">Card title {index + 1}</div>
                            </div>
                        </div>
                    ))}
                </div>
            </div>
        </div>
    );
}
