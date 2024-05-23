import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import axios from 'axios';
import data from './data.json'; // Corrected import statement

export default function Video() {
    const { id } = useParams();
    const navigate = useNavigate();
    const [videos, setVideos] = useState([]);

    useEffect(() => {
        axios.get('http://localhost:18080/api/v1/video/suggestion')
            .then(response => {
                setVideos(response.data.videos);
            })
            .catch(error => {
                console.error('There was an error fetching the videos!', error);
            });
    }, [id]);

    const videoData = data.find(item => item.id === parseInt(id));

    if (!videoData) {
        return <div>Video not found</div>;
    }

    const { title, description, video_url: videoLink } = videoData;

    const handleVideoClick = (video) => {
        console.log('Video clicked:', video);

        const removeQuotes = (str) => {
            if (str.startsWith('"') && str.endsWith('"')) {
                console.log("inside removeQuotes");
                return str.slice(1, -1);
            }
            return str;
        };

        const sanitizedVideo = {
            id: video.id,
            name: removeQuotes(video.name),
            video_link: removeQuotes(video.video_link),
            genres: removeQuotes(video.genres),
            thumbnail_link: removeQuotes(video.thumbnail_link),
            description: removeQuotes(video.description)
        };

        axios.post('http://localhost:18080/api/v1/video', sanitizedVideo)
            .then(response => {
                console.log('Video details sent successfully:', response.data);
                navigate(`/video/${video.id}`);
            })
            .catch(error => {
                console.error('There was an error sending the video details!', error);
            });
    };

    return (
        <div className="flex flex-col items-center justify-center mt-10 w-full px-4">
            <div className="w-full max-w-4xl">
                <div className="aspect-w-16 aspect-h-9">
                    <iframe
                        src={videoLink}
                        title="video player"
                        allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
                        allowFullScreen
                        className="w-full h-full"
                    ></iframe>
                </div>
                <h1 className="text-4xl font-bold mt-4 mb-2">{title}</h1>
                <p className="text-lg">{description}</p>
            </div>
            <div className='mb-10'>
                <h2 className="text-2xl font-bold mt-8">More videos</h2>
                <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-6 mt-4">
                    {videos.map((video, index) => (
                        <div key={index} className="relative cursor-pointer group" onClick={() => handleVideoClick(video)}>
                            <img
                                className="w-full h-48 object-cover rounded-lg"
                                src={video.thumbnail_link.slice(2, -1)}
                                alt={`Thumbnail ${index + 1}`}
                            />
                            <div className="p-4 bg-gray-900 text-white absolute bottom-0 left-0 right-0 opacity-75 group-hover:opacity-100 transition-opacity duration-300">
                                <div className="font-bold text-lg">{video.name}</div>
                            </div>
                        </div>
                    ))}
                </div>
            </div>
        </div>
    );
}
