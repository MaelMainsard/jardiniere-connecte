export const getPlanterCount = (): Promise<number> => {
    return new Promise((resolve) => {
      setTimeout(() => {
        resolve(6);
      }, 1000);
    });
  };