import asyncio


async def main() -> int:
    print("Hello world!")
    return 0


if __name__ == "__main__":
    raise SystemExit(asyncio.run(main()))
