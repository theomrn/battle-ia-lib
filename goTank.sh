echo "Building the Docker image..."
docker build -t battle_bot -f Dockerfile .

echo "Running the Docker container..."
docker run battle_bot

echo "Container battle_bot ran successfully."
