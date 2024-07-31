import { DataInterface } from '../entities/data.interface';
import { DataModel } from '../entities/data.model';

export const getOverviewData = (): Promise<DataInterface> => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(new DataModel(
        Math.floor(Math.random() * 100),
        Math.floor(Math.random() * 100),
        Math.floor(Math.random() * 60),
        Math.floor(Math.random() * 3000),
      ));
    }, 2000);
  });
};