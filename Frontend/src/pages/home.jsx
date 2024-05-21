import React from 'react';

export default function Home() {
    // Array to simulate thumbnails
    const thumbnails = new Array(9).fill('https://via.placeholder.com/1200/700');

    return (
        <div className="text-white">
            <h1 className="text-4xl font-bold mb-4">YouTube Home</h1>
            <hr />
            <div className="grid grid-cols-3 gap-6 mt-10">
                {thumbnails.map((thumbnail, index) => (
                    <div key={index} className="relative rounded-3xl">
                        <div className="bg-gray-800 overflow-hidden" style={{ width: '100%', paddingTop: '50%' }}>
                            <img
                                className="absolute inset-0 w-full h-full object-cover"
                                src={thumbnail}
                                alt="Sunset in the mountains"
                            />
                        </div>
                        <div className="px-4 py-4 absolute bottom-0 left-0 right-0 bg-gray-900 ">
                            <div className="font-bold text-xl mb-2">Card title {index + 1}</div>
                            <p className="text-gray-400 text-base">
                                Some quick example text to build on th
                            </p>
                        </div>
                    </div>
                ))}
            </div>
        </div>
    );
}
