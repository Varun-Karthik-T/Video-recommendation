import React, { useEffect, useState } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom';
import data from './data.json'


export default function Home() {
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
    }, []);

    const handleVideoClick = (video) => {
        console.log('Video clicked:', video);

        const removeQuotesAndSpaces = (str) => {
            if (typeof str !== 'string') return str;
            return str.trim().replace(/^"|"$/g, '');
        };

        const sanitizedVideo = {
            id: video.id,
            name: removeQuotesAndSpaces(video.name),
            video_link: removeQuotesAndSpaces(video.video_link),
            genres: removeQuotesAndSpaces(video.genres),
            thumbnail_link: removeQuotesAndSpaces(video.thumbnail_link),
            description: removeQuotesAndSpaces(video.description)
        };


        console.log("Sanitized video:", sanitizedVideo);

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
        <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-6 mt-10 mx-12 mb-10">
            {videos.map((video) => (
                <div
                    key={video.id}
                    onClick={() => handleVideoClick(video)}
                    className="relative cursor-pointer group"
                >


                    <img

                        className="w-full h-[14.5rem] object-cover rounded-lg"
                        src={video.thumbnail_link.slice(2, -1)}
                        alt={video.name}
                    />
                    <div className="p-4 bg-gray-900 text-white absolute bottom-0 left-0 right-0 opacity-75 group-hover:opacity-100 transition-opacity duration-300">
                        <div className="font-bold text-lg">{video.name.slice(1, -1)}</div>
                        <div>{video.description.slice(2, -1)}</div>

                    </div>
                </div>
            ))}
        </div>
    );
}
