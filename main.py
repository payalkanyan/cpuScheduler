from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from typing import List
import subprocess
import json

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  
    allow_credentials=True,
    allow_methods=["*"], 
    allow_headers=["*"],  
)
class Task(BaseModel):
    id: int
    arrival_time: int
    burst_time: int
    priority: int

class SchedulerRequest(BaseModel):
    algorithm: str
    tasks: List[Task]
    quantum: int = 0

@app.post("/schedule")
def schedule(request: SchedulerRequest):
    tasks = request.tasks
    algorithm = request.algorithm
    quantum = request.quantum

    command = ["./cpu_scheduler", algorithm]
    if algorithm == "rr":
        command.append(str(quantum))

    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode != 0:
        return {"error": "Failed to execute scheduler"}

    scheduled_tasks = json.loads(result.stdout)
    return {"tasks": scheduled_tasks}
