import logging

logging.basicConfig()
logger = logging.getLogger("dynamic_logger")


def main() -> int:
    while True:
        action = input("Input action (test, config, quit): ")
        if action == "test":
            logger.debug("A debug message")
            logger.info("A info message")
            logger.warning("A warning message")
            logger.error("A error message")
            logger.critical("A critial message")
        elif action == "config":
            level = input(
                "Input logging level (debug, info, warning, error, critical): "
            )
            if level == "debug":
                logger.setLevel(logging.DEBUG)
            elif level == "info":
                logger.setLevel(logging.INFO)
            elif level == "warnig":
                logger.setLevel(logging.WARNING)
            elif level == "error":
                logger.setLevel(logging.ERROR)
            elif level == "critical":
                logger.setLevel(logging.CRITICAL)
        elif action == "quit":
            break
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
