import React from 'react';
import { useNavigate } from 'react-router-dom';
import { Separator } from '@/components/ui/separator';

export default function Header() {
  const navigate = useNavigate();

  return (
    <>
      <h1 className="text-4xl font-bold my-5 mx-5 cursor-pointer" onClick={() => navigate("/")}>
        YouTube Home
      </h1>
      <Separator className="my-3" />
    </>
  );
}
